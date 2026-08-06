# První fáze: vygenerování Doxygen dokumentace
FROM alpine:3.22 AS docs-build

RUN apk add --no-cache \
    doxygen \
    graphviz

WORKDIR /app

COPY . .

RUN doxygen Doxyfile

# Build selže, pokud dokumentace nevznikla
RUN test -f /app/docs/html/index.html


# Druhá fáze: webový server
FROM caddy:2-alpine

COPY Caddyfile /etc/caddy/Caddyfile

COPY --from=docs-build /app/docs/html /srv